
namespace TPINTEGRADOR.Models
{
    public enum TipoEntidad
    {
        SUBTERRANEO,
        FERROCARRIL,
        ORGANIZACION
    }

    public static class TipoEntidadExtensions
    {
        public static TipoEntidad? GetType(string type)
        {
            switch (type)
            {
                case "SUBTERRANEO":
                    return TipoEntidad.SUBTERRANEO;
                case "FERROCARRIL":
                    return TipoEntidad.FERROCARRIL;
                case "ORGANIZACION":
                    return TipoEntidad.ORGANIZACION;
                default:
                    return null;

            }
        }

        public static string GetNombre(TipoEntidad type)
        {
            switch (type)
            {
                case TipoEntidad.SUBTERRANEO:
                    return "SUBTERRANEO";
                case TipoEntidad.FERROCARRIL:
                    return "FERROCARRIL";
                case TipoEntidad.ORGANIZACION:
                    return "ORGANIZACION";
                default:
                    return string.Empty;

            }
        }
    }
}
