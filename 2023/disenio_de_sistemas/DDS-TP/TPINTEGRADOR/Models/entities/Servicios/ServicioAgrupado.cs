using Microsoft.AspNetCore.Identity;

namespace TPINTEGRADOR.Models
{
    public class ServicioAgrupado : SuperServicio
    {
        public ServicioAgrupado(List<Servicio> servicios, string nombre, List<Entidad> entidad, ProveedorDeServicio proveedor) : base(nombre, entidad, proveedor)
        {
            Servicios = servicios;
        }

        public List<Servicio> Servicios;
    }
}
