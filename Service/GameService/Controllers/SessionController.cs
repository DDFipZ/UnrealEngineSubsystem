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

    [HttpPost("createsession")]
    public string CreateSession([FromBody] SessionSettings sessionSettings)
    {
        var guid = Guid.NewGuid().ToString();
        sessionSettings.ID = guid;
        string serializedData = JsonSerializer.Serialize(sessionSettings);
        Task task = _cache.StringSet($"SESSION:{sessionSettings.ID}", serializedData);
        _cache.SetAsync($"SESSIONS:{sessionSettings.BuildUniqueID}", sessionSettings.ID);
        return serializedData;  
    }

    [HttpGet("findsessions")]
    public string FindSessions([FromBody] SessionSettings sessionSettings)
    {
        var serialized = JsonSerializer.Serialize(sessionSettings.BuildUniqueID);
        var sessionValues = _cache.SetMembers($"SESSIONS:{serialized}");
        var sessionIDs = sessionValues.ToStringArray();
        
        return JsonSerializer.Serialize(sessionIDs);
    }
}
