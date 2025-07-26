using Microsoft.AspNetCore.Mvc;

namespace GameService.Controllers;

[ApiController]
[Route("[controller]")]
public class WeatherForecastController : ControllerBase
{
    private static readonly string[] Summaries = new[]
    {
        "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
    };

    private readonly ILogger<WeatherForecastController> _logger;
    private readonly IRedisCacheService _cache;

    public WeatherForecastController(ILogger<WeatherForecastController> logger, IRedisCacheService cache)
    {
        _logger = logger;
        _cache = cache;
    }

    [HttpGet("weather")]
    public IEnumerable<WeatherForecast> GetForecast()
    {
        return Enumerable.Range(1, 5).Select(index => new WeatherForecast
        {
            Date = DateOnly.FromDateTime(DateTime.Now.AddDays(index)),
            TemperatureC = Random.Shared.Next(-20, 55),
            Summary = Summaries[Random.Shared.Next(Summaries.Length)]
        })
        .ToArray();
    }

    [HttpGet("HelloWorld")]
    public string HelloWorld()
    {
        return "Hello World from GameService!";
    }

    [HttpPost("SetKey")]
    public string SetKey()
    {
        TimeSpan expiry = TimeSpan.FromMinutes(10);
        Task task = _cache.SetAsync("my_key", "my_value", expiry);
        if (task.IsCompleted)
        {
            return "Value set!";
        }
        return "Value not set!";
    }

    [HttpGet("GetKey")]
    public async Task<String?> GetKey()
    {
        var task = await _cache.GetAsync("my_key");
        return task;
    }
}
