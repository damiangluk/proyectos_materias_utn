namespace TPINTEGRADOR.Models
{

    public sealed class SistemaServiciosPublicos
    {
        #region instance
        private static readonly SistemaServiciosPublicos instance = new SistemaServiciosPublicos();

        private SistemaServiciosPublicos() { }

        public static SistemaServiciosPublicos GetInstance
        {
            get { return instance; }
        }
        #endregion

        #region properties
        public List<Organismo> Organismos { get; set; } = new List<Organismo>();

        #endregion

        #region methods
        public bool AgregarOrganismo(string[] columns)
        {
            if (columns.Length < 2)
                throw new Exception("Se intento crear un organismo sin informacion");

            TipoOrganismo? tipoOrganismo = TipoOrganismoExtensions.GetType(columns[0].Trim());

            if (!tipoOrganismo.HasValue) return false;
            if (Organismos.Any(o => o.Nombre.Equals(columns[1]))) return false;

            Organismo organismo = new Organismo(tipoOrganismo.Value, columns[1].Trim());

            Organismos.Add(organismo);

            return true;
        }

        public bool AgregarOrganismo(Organismo organismo)
        {
            if(Organismos.Any(o => o.Nombre.Equals(organismo.Nombre)))
                return false;

            Organismos.Add(organismo);

            return true;
        }
        #endregion
    }
}