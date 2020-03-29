using System.Collections.Generic;

namespace fireland15.LindenmayerSystem.Expressions
{
    class EvaluationContext : IEvaluationContext
    {
        private readonly IReadOnlyDictionary<string, Variable> variables;

        public IEnumerable<Variable> Variables => variables.Values;

        public EvaluationContext(IReadOnlyDictionary<string, Variable> variables)
        {
            this.variables = variables;
        }

        public Variable GetVariable(string symbol)
        {
            return variables[symbol];
        }
    }
}
