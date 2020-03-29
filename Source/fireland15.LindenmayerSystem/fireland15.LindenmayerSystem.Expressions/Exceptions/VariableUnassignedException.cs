using System;

namespace fireland15.LindenmayerSystem.Expressions.Exceptions
{
    public class ValueUndefinedException : Exception
    {
        public string Symbol { get; }

        public ValueUndefinedException(string symbol, Exception innerException = null)
            : base(GetErrorMessage(symbol), innerException)
        {
        }

        private static string GetErrorMessage(string symbol)
        {
            return $"Value undefined. '{symbol}' does not have a value assigned.";
        }
    }
}
