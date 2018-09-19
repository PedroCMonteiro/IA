using System.Collections.Generic;

namespace IACsharp
{
    public class Grafo
    {
        private List<Aresta>[] arestas = new List<Aresta>[0];        

        public Grafo(int c)
        {
            arestas = new List<Aresta>[c];
        }

        public int NumeroDeCidades()
        {
            return arestas.Length;
        }

        
    }
}
