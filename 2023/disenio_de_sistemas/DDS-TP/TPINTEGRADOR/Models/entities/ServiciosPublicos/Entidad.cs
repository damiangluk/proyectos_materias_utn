
using Microsoft.AspNetCore.Identity;

namespace TPINTEGRADOR.Models
{
    public class Entidad : Identidad
    {
        public Entidad(string nombre, TipoEntidad tipoEntidad, List<Localizacion> localizaciones) 
        {
            Nombre = nombre;
            TipoEntidad = tipoEntidad;
            Localizaciones = localizaciones;
            Servicios = new List<SuperServicio>();
        }

        public string Nombre;
        public TipoEntidad TipoEntidad;
        public List<Localizacion> Localizaciones;
        public List<SuperServicio> Servicios;
        //Sucursales
    }
}
