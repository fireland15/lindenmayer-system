using System;

namespace fireland15.LindenmayerSystem.Expressions.Exceptions
{
    public class ParseException : Exception
    {
        public ParseException(string message, Exception innerException = null)
            : base(message, innerException) { }
    }
}
