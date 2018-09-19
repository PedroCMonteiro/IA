using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IACsharp
{
    class Aresta
    {
        double peso { get; set; }
        int no { get; set; }

        public Aresta(double peso, int no)
        {
            this.no = no;
            this.peso = peso;

        }
    }
}
