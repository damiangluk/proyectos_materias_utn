namespace TPINTEGRADOR.Models
{
    public enum Rol
    {
        USUARIOAFECTADO,
        OBSERVADOR
    }

    public static class RolExtensions
    {
        public static Rol? GetType(string type)
        {
            switch (type)
            {
                case "USUARIOAFECTADO":
                    return Rol.USUARIOAFECTADO;
                case "OBSERVADOR":
                    return Rol.OBSERVADOR;
                default:
                    return null;

            }
        }

        public static string GetTipo(Rol type)
        {
            switch (type)
            {
                case Rol.USUARIOAFECTADO:
                    return "USUARIOAFECTADO";
                case Rol.OBSERVADOR:
                    return "OBSERVADOR";
                default:
                    return string.Empty;

            }
        }
    }
}
