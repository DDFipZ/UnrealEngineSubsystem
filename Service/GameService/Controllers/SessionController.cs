using Microsoft.AspNetCore.Mvc;
using Microsoft.OpenApi;
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
        _cache.SetAsync($"ACTIVE_SESSIONS:{sessionSettings.BuildUniqueID}", sessionSettings.ID);
        return serializedData;  
    }
}
