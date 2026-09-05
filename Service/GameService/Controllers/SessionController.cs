using Microsoft.AspNetCore.Mvc;
using Microsoft.OpenApi;
using StackExchange.Redis;
using System.Text.Json;

namespace GameService.Controllers;

[ApiController]
[Route("[controller]")]
public class SessionController : ControllerBase
{

    private readonly ILogger<SessionController> _logger;
    private readonly IRedisCacheService _cache;

    public SessionController(ILogger<SessionController> logger, IRedisCacheService cache)
    {
        _logger = logger;
        _cache = cache;
    }

    [HttpGet("ping")]
    public string Ping()
    {
        return "Connected!";
    }
    
    [HttpPost("createsession")]
    public SessionSettings CreateSession([FromBody] SessionSettings sessionSettings)
    {
        // Get IP from request
        sessionSettings.IPAddress = HttpContext.Connection.RemoteIpAddress?.ToString() ?? "Unknown";
        var guid = Guid.NewGuid().ToString();
        sessionSettings.sessionId = guid;
        HashEntry[] hashEntries =
        [
            new HashEntry("sessionId", sessionSettings.sessionId),
            new HashEntry("IPAddress", sessionSettings.IPAddress),
            new HashEntry("Name", sessionSettings.Name),
            new HashEntry("BuildUniqueID", (RedisValue)sessionSettings.BuildUniqueID)
        ];
        // Save the session as a hash in Redis
        _cache.HashSetAsync($"SESSION:{sessionSettings.sessionId}", hashEntries);
        
        // Adds the session to the set of sessions for the given BuildUniqueID
        _cache.SetAsync($"SESSIONS:{sessionSettings.BuildUniqueID}", sessionSettings.sessionId);
        
        return sessionSettings;
    }

    [HttpGet("findsessions")]
    public List<SessionSettings> FindSessions([FromBody] SessionSettings sessionSettings)
    {
        RedisValue[] sessionValues = _cache.SetMembers($"SESSIONS:{sessionSettings.BuildUniqueID}");
        List <SessionSettings> sessions = new List<SessionSettings>();
        foreach (var session in sessionValues)
        {
            HashEntry[] entries = _cache.HashGetAllAsync($"SESSION:{session.ToString()}").Result;
            SessionSettings foundSession = new SessionSettings
            {
                sessionId = entries.FirstOrDefault(e => e.Name == "sessionId").Value,
                IPAddress = entries.FirstOrDefault(e => e.Name == "IPAddress").Value,
                Name = entries.FirstOrDefault(e => e.Name == "Name").Value,
                BuildUniqueID = (int)entries.FirstOrDefault(e => e.Name == "BuildUniqueID").Value
            };
            
            sessions.Add(foundSession);
        }
        return sessions;
    }

    [HttpPost("{sessionId}/offer")]
    public IActionResult PostOffer([FromRoute] string sessionId, [FromBody] WebRtcOffer offer)
    {
        if (string.IsNullOrEmpty(sessionId))
            return BadRequest("Session ID is required");

        if (offer == null || string.IsNullOrEmpty(offer.Description))
            return BadRequest("Offer description is required");

        try
        {
            // Store the SDP offer in Redis
            var offerKey = $"OFFER:{sessionId}";
            var offerData = JsonSerializer.Serialize(offer);
            _cache.SetAsync(offerKey, offerData);

            _logger.LogInformation($"✅ Stored SDP offer for session {sessionId}");
            return Ok(new { message = "Offer stored successfully", sessionId = sessionId });
        }
        catch (Exception ex)
        {
            _logger.LogError($"❌ Error storing offer: {ex.Message}");
            return StatusCode(500, "Error storing offer");
        }
    }

    [HttpGet("{sessionId}/offer")]
    public IActionResult GetOffer([FromRoute] string sessionId)
    {
        if (string.IsNullOrEmpty(sessionId))
            return BadRequest("Session ID is required");

        try
        {
            var offerKey = $"OFFER:{sessionId}";
            var offerData = _cache.GetAsync(offerKey).Result;

            if (string.IsNullOrEmpty(offerData))
                return NotFound(new { message = "No offer found for this session", sessionId = sessionId });

            var offer = JsonSerializer.Deserialize<WebRtcOffer>(offerData);
            _logger.LogInformation($"✅ Retrieved SDP offer for session {sessionId}");
            return Ok(offer);
        }
        catch (Exception ex)
        {
            _logger.LogError($"❌ Error retrieving offer: {ex.Message}");
            return StatusCode(500, "Error retrieving offer");
        }
    }

    [HttpPost("{sessionId}/candidate")]
    public IActionResult PostCandidate([FromRoute] string sessionId, [FromBody] IceCandidate candidate)
    {
        if (string.IsNullOrEmpty(sessionId))
            return BadRequest("Session ID is required");

        if (candidate == null || string.IsNullOrEmpty(candidate.Candidate))
            return BadRequest("Candidate is required");

        try
        {
            var candidatesKey = $"CANDIDATES:{sessionId}";
            var candidateData = JsonSerializer.Serialize(candidate);
            
            // Add candidate to a list in Redis
            _cache.ListRightPushAsync(candidatesKey, candidateData);

            _logger.LogInformation($"✅ Stored ICE candidate for session {sessionId}");
            return Ok(new { message = "Candidate stored successfully", sessionId = sessionId });
        }
        catch (Exception ex)
        {
            _logger.LogError($"❌ Error storing candidate: {ex.Message}");
            return StatusCode(500, "Error storing candidate");
        }
    }

    [HttpGet("{sessionId}/candidates")]
    public IActionResult GetCandidates([FromRoute] string sessionId)
    {
        if (string.IsNullOrEmpty(sessionId))
            return BadRequest("Session ID is required");

        try
        {
            var candidatesKey = $"CANDIDATES:{sessionId}";
            var candidatesList = _cache.ListRangeAsync(candidatesKey, 0, -1).Result;

            if (candidatesList.Length == 0)
                return NotFound(new { message = "No candidates found for this session", sessionId = sessionId });

            var candidates = candidatesList
                .Where(c => !c.IsNullOrEmpty)
                .Select(c => JsonSerializer.Deserialize<IceCandidate>(c.ToString()))
                .ToList();

            _logger.LogInformation($"✅ Retrieved {candidates.Count} ICE candidates for session {sessionId}");
            return Ok(candidates);
        }
        catch (Exception ex)
        {
            _logger.LogError($"❌ Error retrieving candidates: {ex.Message}");
            return StatusCode(500, "Error retrieving candidates");
        }
    }
}
