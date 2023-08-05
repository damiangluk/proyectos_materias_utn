
using Microsoft.AspNetCore.Identity;
using TPINTEGRADOR.Models;

namespace TPINTEGRADOR.Models
{
    public class Organismo : Identidad
    {
        public Organismo(TipoOrganismo tipoOrganismo, string nombre)
        {
            TipoOrganismo = tipoOrganismo;
            Nombre = nombre;
        }

        public TipoOrganismo TipoOrganismo;
        public string Nombre;
        public Persona Encargado;        public List<Entidad> Entidades;

        public object OrganismosForFront()
        {
            object organismosFront = new
            {
                tipoOrganismo = TipoOrganismoExtensions.GetNombre(TipoOrganismo),
                nombreOrganismo = Nombre,
            };

            return organismosFront;
        }
        
    }
}