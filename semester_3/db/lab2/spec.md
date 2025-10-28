# Dalykinė sritis: Siuntinių logistikos centras
### Laukai:
- Paketas: id, kilmės_šalis, destinacija, kompanija, prekė[], svoris_kg
- Kompanija: pav, limitas_kg, kaina/kg
- Prekė: pav, tipas, kaina_eur, svoris_kg
- Žingsnis: paketas, iš, į, būsena, completion_data

pvz: 
Paketas1: L0651947, "Lietuva", "Lietuva", Prekė11, 0.75
Kompanija1: UPS, 50, 0.72
Prekė11: "House of Leaves", knygos, 15, 0.75

Paketas2: I0051934, "Kinija", "Vokietija", [Prekė21, Prekė22], 2.1
Kompanija1: FedEx, 10, 0.65
Prekė21: "Midnight black kelnės", drabužiai, 35.50, 1.9
Prekė22: "HyperAmp 4000 pakrovėjas", smulki_elektronika, 6.1, 0.2

Žingsnis: L0651947, "Prienų paštas", "Kauno sandėlys", Įvykdyta, 2025-10-10
Žingsnis: L0651947, "Kauno sandėlys", "Vilniaus rūšiavimo centras", Vykdoma, NULL
Žingsnis: L0651947, "Vilniaus rūšiavimo centras", "Trakų paštas", Laukiama, NULL

## Komandos
CreatePacket, DeletePacket, AddItem, RemoveItem
CreateItem, DeleteItem, ChangePrice
AddCompany, DeleteCompany, ChangeLimit, ChangeRate,
AddStep, AdvanceState
Bunch of filters