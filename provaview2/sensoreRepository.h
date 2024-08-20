public class SensoreRepository{
    List<sensoriDanno> sensoriDanno;
//dependecy injection non la uso nella relazione
    public:
        SensoreDanno GetSensoreByName(string name){
            for(i = sensoriDanno.begin(); i == sensori.end(); ++i){
                if i.getNome() == name{
                    return i;
                }
            }
        }

        void AddSensore(SensoreDanno* sensore){
            // il chiamante ha già verificato che non esiste un sensore avente lo stesso nome
            sensoriDanno.push_back(sensore);
        }

        RemoveSensore(SensoreDanno* sensore){
            //il chiamante ha chiamato la GetSensoreByName, riceve il sensore per puntatore quindi posso provare a rimuoverlo direttamente
            sensoriDanno.erease(sensore);
        }
}