using StackExchange.Redis;

public interface IRedisCacheService
{
    Task SetAsync(string key, string value, TimeSpan? expiry = null);
    Task StringSet(string key, string value, TimeSpan? expiry = null);
    Task HashSetAsync(string key, HashEntry[] hashFields, TimeSpan? expiry = null);
    Task<HashEntry[]> HashGetAllAsync(string key);
    RedisValue[] SetMembers(string key);
    Task<string?> GetAsync(string key);
    Task<bool> RemoveAsync(string key);
    Task<bool> KeyExistsAsync(string key);
    Task ListRightPushAsync(string key, string value);
    public Task<RedisValue[]> ListRangeAsync(string key, long start, long stop);
}