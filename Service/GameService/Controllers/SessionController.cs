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
        sessionSettings.ID = guid;
        HashEntry[] hashEntries =
        [
            new HashEntry("ID", sessionSettings.ID),
            new HashEntry("IPAddress", sessionSettings.IPAddress),
            new HashEntry("Name", sessionSettings.Name),
            new HashEntry("BuildUniqueID", sessionSettings.BuildUniqueID)
        ];
        // Save the session as a hash in Redis
        Task task = _cache.HashSetAsync($"SESSION:{sessionSettings.ID}", hashEntries);
        
        // Adds the session to the set of sessions for the given BuildUniqueID
        _cache.SetAsync($"SESSIONS:{sessionSettings.BuildUniqueID}", sessionSettings.ID);
        
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
                ID = entries.FirstOrDefault(e => e.Name == "ID").Value,
                Name = entries.FirstOrDefault(e => e.Name == "Name").Value,
                BuildUniqueID = (int)entries.FirstOrDefault(e => e.Name == "BuildUniqueID").Value
            };
            
            sessions.Add(foundSession);
        }
        return sessions;
    }
}
