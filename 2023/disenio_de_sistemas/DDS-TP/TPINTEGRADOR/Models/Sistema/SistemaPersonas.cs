namespace TPINTEGRADOR.Models
{
    public sealed class SistemaPersonas
    {
        #region instance
        
        private static readonly SistemaPersonas instance = new SistemaPersonas();

        private SistemaPersonas() { }

        public static SistemaPersonas GetInstance
        {
            get { return instance; }
        }
        
        #endregion

        #region properties
        
        public List<Comunidad> Comunidades { get; set; } = new List<Comunidad>();
        public List<Participacion> Participaciones { get; set; } = new List<Participacion>();

        #endregion
    }
}