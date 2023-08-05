using System.Collections.Generic;
using System.Linq;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Text;

namespace TPINTEGRADOR.Models
{
    public class LectorCSV
    {
        public bool Valido = true;
        public string Error = "";

        public async Task<List<string[]>> LeerArchivo(IFormFile archivoCSV)
        {
            if (!Path.GetExtension(archivoCSV.FileName).Equals(".csv", StringComparison.OrdinalIgnoreCase))
            {
                Valido = false;
                Error = "El archivo ingresado no es un CSV";
                return new List<string[]>();
            }

            string[] rows;
            using (var reader = new StreamReader(archivoCSV.OpenReadStream(), Encoding.Latin1))
            {
                string contents = await reader.ReadToEndAsync();
                rows = contents.Split(new string[] { "\n", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);
            }

            if (rows.Length < 2 || string.IsNullOrEmpty(rows[1]))
            {
                Valido = false;
                Error = "El archivo ingresado es invalido";
                return new List<string[]>();
            }

            List<string[]> rowsSplited = rows.Select(r => r.Split(new string[] { ",", ";" }, StringSplitOptions.None)).ToList();

            return rowsSplited;
        }
    }

}
