namespace TPINTEGRADOR.Models
{
    public class Servicio : SuperServicio
    {
        public Servicio(string descripcion, string nombre, List<Entidad> entidad, ProveedorDeServicio proveedor) : base(nombre, entidad, proveedor)
        {
            Descripcion = descripcion;
        }

        public string Descripcion;
    }
}
