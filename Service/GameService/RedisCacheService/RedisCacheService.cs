
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

    public Task HashSetAsync(string key, HashEntry[] hashFields, TimeSpan? expiry = null)
    {
        try
        {
            _cache.HashSet(key, hashFields);
            _cache.KeyExpire(key, expiry);
            return Task.CompletedTask;
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            return Task.FromException(e);
        }

    }

    public Task<HashEntry[]> HashGetAllAsync(string key)
    {
        return _cache.HashGetAllAsync(key);

    }

    Task IRedisCacheService.SetAsync(string key, string value, TimeSpan? expiry)
    {
        _cache.SetAddAsync(key, value);
        return Task.CompletedTask;
    }
    public RedisValue[] SetMembers(string key)
    {
        return _cache.SetMembers(key);

    }
    
    public Task ListRightPushAsync(string key, string value)
    {
        return _cache.ListRightPushAsync(key, value);
    }

    public Task<RedisValue[]> ListRangeAsync(string key, long start, long stop)
    {
        return _cache.ListRangeAsync(key, start, stop);
    }
}