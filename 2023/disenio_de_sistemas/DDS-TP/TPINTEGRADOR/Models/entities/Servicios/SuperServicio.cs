
namespace TPINTEGRADOR.Models
{
    public abstract class SuperServicio : Identidad
    {
        public SuperServicio(string nombre, List<Entidad> entidades, ProveedorDeServicio proveedor)
        {
            Nombre = nombre;
            Entidades = entidades;
            Proveedor = proveedor;
            Incidentes = new List<Incidente>();
            Comunidades = new List<Comunidad>();

        }

        public string Nombre;
        public List<Entidad> Entidades;
        public ProveedorDeServicio Proveedor;
        public List<Incidente> Incidentes;
        public List<Comunidad> Comunidades;
    }
}
