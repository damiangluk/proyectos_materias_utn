using System.Collections.Generic;
using System.Linq;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace TPINTEGRADOR.Models
{
    public class GeoApiParam
    {
        public List<Param> Param { get; set; } = new List<Param>();
    }

    public class Param
    {
        public string nombre { get; set; } = string.Empty;
        public string campos { get; set; } = string.Empty;
        public int max { get; set; }
        public bool exacto { get; set; }
    }
}
