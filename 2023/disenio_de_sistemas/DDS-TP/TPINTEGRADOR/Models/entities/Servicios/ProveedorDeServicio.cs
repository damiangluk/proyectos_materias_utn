namespace TPINTEGRADOR.Models
{
    public abstract class ProveedorDeServicio : Identidad
    {
        public ProveedorDeServicio(string nombre, List<SuperServicio> superServicio)
        {
            Nombre = nombre;
            SuperServicio = superServicio;
        }

        public string Nombre;
        public List<SuperServicio> SuperServicio;
    }
}