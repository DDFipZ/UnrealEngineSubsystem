
using StackExchange.Redis;

internal class RedisCacheService : IRedisCacheService
{
    private readonly IDatabase _cache;

    public RedisCacheService(IConnectionMultiplexer redis)
    {
        _cache = redis.GetDatabase();
    }
    async Task<string?> IRedisCacheService.GetAsync(string key)
    {
        return await _cache.StringGetAsync(key);
    }

    Task<bool> IRedisCacheService.KeyExistsAsync(string key)
    {
        throw new NotImplementedException();
    }

    Task<bool> IRedisCacheService.RemoveAsync(string key)
    {
        throw new NotImplementedException();
    }

    Task IRedisCacheService.SetAsync(string key, string value, TimeSpan? expiry)
    {
        _cache.StringSet(key, value);
        _cache.KeyExpire(key, expiry);
        return Task.CompletedTask;
    }
}