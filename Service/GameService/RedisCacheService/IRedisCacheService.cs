using StackExchange.Redis;

public interface IRedisCacheService
{
    Task SetAsync(string key, string value, TimeSpan? expiry = null);
    Task StringSet(string key, string value, TimeSpan? expiry = null);
    RedisValue[] SetMembers(string key);
    Task<string?> GetAsync(string key);
    Task<bool> RemoveAsync(string key);
    Task<bool> KeyExistsAsync(string key);
}