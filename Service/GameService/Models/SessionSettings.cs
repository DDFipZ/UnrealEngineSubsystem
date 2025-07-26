namespace GameService;

enum GameID
{
    LetItRipCity,
    LetItRipCountry
}
public class SessionSettings
{
    public string? ID { get; set; }
    public string Name { get; set; }
    public int BuildUniqueID { get; set; }
}
