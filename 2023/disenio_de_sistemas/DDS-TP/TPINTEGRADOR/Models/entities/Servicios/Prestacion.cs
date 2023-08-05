
using Microsoft.AspNetCore.Identity;

namespace TPINTEGRADOR.Models
{
    public class Prestacion : Identidad
    {
        public Prestacion(SuperServicio servicio/*, Establecimiento establecimiento*/, bool habilitado) 
        {
            Servicio = servicio;
            //Establecimiento = establecimiento;
            Habilitado = habilitado;
        }

        public SuperServicio Servicio;
        //public Establecimiento Establecimiento;
        public bool Habilitado;
    }
}
