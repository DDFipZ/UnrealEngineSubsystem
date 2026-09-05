namespace GameService;

enum GameID
{
    LetItRipCity,
    LetItRipCountry
}
public class SessionSettings
{
    public string? sessionId { get; set; }
    public string? Name { get; set; }
    public string? IPAddress { get; set; }
    public int BuildUniqueID { get; set; }
}
