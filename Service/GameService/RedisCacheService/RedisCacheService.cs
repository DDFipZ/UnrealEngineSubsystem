
using StackExchange.Redis;
using StackExchange.Redis.Profiling;

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

    Task IRedisCacheService.StringSet(string key, string value, TimeSpan? expiry)
    {
        _cache.StringSetAsync(key, value);
        _cache.KeyExpire(key, expiry);
        return Task.CompletedTask;
    }

    Task IRedisCacheService.SetAsync(string key, string value, TimeSpan? expiry)
    {
        _cache.SetAddAsync(key, value);
        return Task.CompletedTask;
    }
    public RedisValue[] SetMembers(string key)
    {
        Console.WriteLine(_cache.SetMembers(key));
        return _cache.SetMembers(key);

    }
}