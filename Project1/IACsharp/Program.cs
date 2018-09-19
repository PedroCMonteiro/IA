using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace IACsharp
{
    public class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>

        static void Main()
        {
            int cidades = 0;
            List<Aresta>[] arestas;
            string format= "";
            string aux;
            string[] auxd;
            StreamReader file = new StreamReader("brazil58.tsp");
            while (true)
            {
                aux = file.ReadLine();
                auxd = aux.Split(' ');
                foreach (string d in auxd)
                {
                    if (d.Contains("DIMENSION"))
                    {
                        //if(Int32.TryParse(auxd[auxd]))
                    }
                }
                break;
            }

            arestas = new List<Aresta>[cidades];

            Grafo grafo = new Grafo(cidades);
            switch (format)
            {
                case "FULL_MATRIX":
                    FullMatrix(file, arestas);
                    break;

                case "UPPER_COL":
                    UpperCol(file, arestas);
                    break;

                case "UPPER_ROW":
                    UpperRow(file, arestas);
                    break;

                case "UPPER_DIAG_ROW":
                    UpperDiagRow(file, arestas);
                    break;

                case "UPPER_DIAG_COL":
                    UpperDiagCol(file, arestas);
                    break;

                case "LOWER_DIAG_COL":
                    LowerDiagCol(file, arestas);
                    break;

                case "LOWER_DIAG_ROW":
                    LowerDiagRow(file, arestas);
                    break;

                case "LOWER_COL":
                    LowerCol(file, arestas);
                    break;

                case "LOWER_ROW":
                    LowerRow(file, arestas);
                    break;

                default:
                    Console.WriteLine("Format unkown");
                    break;
            }

            Dictionary<int, double> caminho = new Dictionary<int, double>();
            
            for(int i = 0; i< arestas.Length;i++)
            {
                arestas[i].Sort();
            }

            CriaMenorCaminho(arestas);

        }

        private static void FullMatrix(StreamReader file, List<Aresta>[] arestas)
        {
            double peso = 0;
            int check = 1;
            Aresta a;
            for (int i = 0; i < arestas.Length; i++)
            {
                for (int j = 0; j < arestas.Length - 1; j++)
                {
                    check = file.Read();

                    if (j > i)
                    {
                        a = new Aresta(peso, j);
                        arestas[i].Add(a);
                        arestas[i].Sort();
                        a = new Aresta(peso, i);
                        arestas[j].Add(a);
                        arestas[j].Sort();
                        //grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
                        //grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
                    }
                }
            }
        }

        private static void LowerRow(StreamReader file, List<Aresta>[] arestas)
        {
            throw new NotImplementedException();
        }

        private static void LowerCol(StreamReader file, List<Aresta>[] arestas)
        {
            throw new NotImplementedException();
        }

        private static void LowerDiagRow(StreamReader file, List<Aresta>[] arestas)
        {
            throw new NotImplementedException();
        }

        private static void LowerDiagCol(StreamReader file, List<Aresta>[] arestas)
        {
            throw new NotImplementedException();
        }

        private static void UpperDiagCol(StreamReader file, List<Aresta>[] arestas)
        {
            throw new NotImplementedException();
        }

        private static void UpperDiagRow(StreamReader file, List<Aresta>[] arestas)
        {
            throw new NotImplementedException();
        }

        private static void UpperRow(StreamReader file, List<Aresta>[] arestas)
        {
            double peso = 0;
            Aresta a;
            int check = 0;
            for (int i = 0; i < arestas.Length - 1; i++)
            {
                for (int j = i + 1; j < arestas.Length; j++)
                {
                    check = file.Read();
                    //fscanf(arq, "%f", &peso);
                    a = new Aresta(peso, j);
                    arestas[i].Add(a);
                    arestas[i].Sort();
                    a = new Aresta(peso, i);
                    arestas[j].Add(a);
                    arestas[j].Sort();
                    //grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
                    //grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
                }
            }
        }

        private static void UpperCol(StreamReader file, List<Aresta>[] arestas)
        {
            throw new NotImplementedException();
        }

        private static void CriaMenorCaminho(List<Aresta>[] arestas)
        {
            
        }
    }    
}