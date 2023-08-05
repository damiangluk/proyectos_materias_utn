
namespace TPINTEGRADOR.Models
{
    public class GeoApiResponse
    {
        public List<Resultado> resultados { get; set; } = new List<Resultado>();
    }

    public class Resultado
    {
        public int cantidad { get; set; }
        public List<LocalizacionAPI> provincias { get; set; } = new List<LocalizacionAPI>();
        public List<LocalizacionAPI> municipios { get; set; } = new List<LocalizacionAPI>();
        public List<LocalizacionAPI> departamentos { get; set; } = new List<LocalizacionAPI>();

    }

    public class LocalizacionAPI
    {
        public int id { get; set; }
        public string nombre { get; set; } = string.Empty;
    }
}
