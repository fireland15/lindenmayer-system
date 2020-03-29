namespace fireland15.LindenmayerSystem.Expressions
{
    public class Variable
    {
        public string Symbol { get; }

        public float? Value { get; set; }

        public bool IsAssigned => Value.HasValue;

        public Variable(string symbol)
        {
            Symbol = symbol;
        }
    }
}
