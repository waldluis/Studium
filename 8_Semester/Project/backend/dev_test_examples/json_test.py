
test_dict = {
    "PlantData": [ {"PlantID":1, "Test": 0}, {"PlantID": 2, "Test": 0}],
    "ActionID": "SUIIII"
}


plant_ids = []
for i in test_dict["PlantData"]:
    plant_ids.append(i["PlantID"])

print(plant_ids)
