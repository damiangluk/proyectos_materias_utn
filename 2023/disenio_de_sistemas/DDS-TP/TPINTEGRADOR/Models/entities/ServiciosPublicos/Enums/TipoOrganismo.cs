
namespace TPINTEGRADOR.Models
{
    public enum TipoOrganismo
    {
        EMPRESA,
        ORGANISMODECONTROL
    }

    public static class TipoOrganismoExtensions
    {
        public static TipoOrganismo? GetType(string type)
        {
            switch (type)
            {
                case "EMPRESA":
                    return TipoOrganismo.EMPRESA;
                case "ORGANISMODECONTROL":
                    return TipoOrganismo.ORGANISMODECONTROL;
                default:
                    return null;

            }
        }

        public static string GetNombre(TipoOrganismo type)
        {
            switch (type)
            {
                case TipoOrganismo.EMPRESA:
                    return "EMPRESA";
                case TipoOrganismo.ORGANISMODECONTROL:
                    return "ORGANISMODECONTROL";
                default:
                    return string.Empty;

            }
        }
    }
}
