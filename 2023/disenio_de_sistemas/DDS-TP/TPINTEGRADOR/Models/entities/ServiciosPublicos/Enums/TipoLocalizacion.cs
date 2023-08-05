
namespace TPINTEGRADOR.Models
{
    public enum TipoLocalizacion
    {
        MUNICIPIO,
        DEPARTAMENTO,
        PROVINCIA
    }

    public static class TipoLocalizacionExtensions
    {
        public static TipoLocalizacion? GetType(string type)
        {
            switch (type)
            {
                case "MUNICIPIO":
                    return TipoLocalizacion.MUNICIPIO;
                case "DEPARTAMENTO":
                    return TipoLocalizacion.DEPARTAMENTO;
                case "PROVINCIA":
                    return TipoLocalizacion.PROVINCIA;
                default:
                    return null;

            }
        }public static string GetNombre(TipoLocalizacion type)
        {
            switch (type)
            {
                case TipoLocalizacion.MUNICIPIO:
                    return "MUNICIPIO";
                case TipoLocalizacion.DEPARTAMENTO:
                    return "DEPARTAMENTO";
                case TipoLocalizacion.PROVINCIA:
                    return "PROVINCIA";
                default:
                    return string.Empty;

            }
        }
    }
}
