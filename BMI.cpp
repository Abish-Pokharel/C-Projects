#include <iostream>
#include <iomanip>

using namespace std;

double convertWeightToKg(double weight, int unit) {
    switch (unit) {
        case 1: 
            return weight * 0.453592;
        case 2: 
            return weight;
        case 3: 
            return weight / 1000.0;
        case 4: 
            return weight * 907.185;
        case 5: 
            return weight * 0.0283495;
        default:
            return -1; 
    }
}

double convertHeightToMeters(double height, int unit) {
    switch (unit) {
        case 1: 
            return height;
        case 2: 
            return height / 100.0;
        case 3: 
            return height / 1000.0;
        case 4: 
            return height * 0.3048;
        case 5: 
            return height * 0.0254;
        default:
            return -1; 
    }
}

// Provide dietary suggestions based on BMI category
void suggestDiet(double bmi) {
    if (bmi < 18.5) {
        cout << "\nYou are underweight." << endl;
        cout << "Dietary Suggestions:" << endl;
        cout << "- Increase caloric intake with nutrient-dense foods." << endl;
        cout << "- Include protein-rich foods such as lean meats, dairy, and legumes." << endl;
        cout << "- Eat healthy fats from sources like avocados, nuts, and olive oil." << endl;
    } else if (bmi >= 18.5 && bmi < 24.9) {
        cout << "\nYou have a normal weight." << endl;
        cout << "Dietary Suggestions:" << endl;
        cout << "- Maintain a balanced diet with a variety of foods." << endl;
        cout << "- Include fruits, vegetables, whole grains, and lean proteins." << endl;
        cout << "- Ensure adequate hydration and moderate portion sizes." << endl;
    } else if (bmi >= 25.0 && bmi < 29.9) {
        cout << "\nYou are overweight." << endl;
        cout << "Dietary Suggestions:" << endl;
        cout << "- Focus on reducing caloric intake while maintaining nutritional balance." << endl;
        cout << "- Incorporate more fruits, vegetables, and whole grains into your meals." << endl;
        cout << "- Limit intake of sugary and high-fat foods." << endl;
    } else {
        cout << "\nYou are obese." << endl;
        cout << "Dietary Suggestions:" << endl;
        cout << "- Follow a structured weight loss plan under the guidance of a healthcare provider." << endl;
        cout << "- Emphasize portion control and nutrient-dense foods." << endl;
        cout << "- Increase physical activity and avoid high-calorie, low-nutrient foods." << endl;
    }
}

int main() {
    int weightUnit, heightUnit;
    double weight, height;
    cout << ""<< endl;
    cout << "Select weight unit:" << endl;
    cout << "           1. Pound" << endl;
    cout << "           2. Kilogram" << endl;
    cout << "           3. Gram" << endl;
    cout << "           4. Ton" << endl;
    cout << "           5. Ounce" << endl;
    cout << "           6. Exit" << endl;
    cout << ""<< endl;
    cout << "Enter your choice: ";
    cin >> weightUnit;

    if (weightUnit == 6) {
        cout << "Exiting..." << endl;
        return 0;
    }

    cout << ""<< endl;
    cout << "Enter weight: ";
    cin >> weight;
     cout << ""<< endl;

    cout << "\nSelect height unit:" << endl;
    cout << "1. Meter" << endl;
    cout << "2. Centimeter" << endl;
    cout << "3. Millimeter" << endl;
    cout << "4. Foot" << endl;
    cout << "5. Inch" << endl;
    cout << "6. Exit" << endl;
     cout << ""<< endl;
    cout << "Enter your choice: ";
    cin >> heightUnit;

    if (heightUnit == 6) {
        cout << "Exiting..." << endl;
        return 0;
    }

    cout << "Enter height: ";
    cin >> height;

    double weightInKg = convertWeightToKg(weight, weightUnit);
    double heightInMeters = convertHeightToMeters(height, heightUnit);

    if (weightInKg < 0 || heightInMeters < 0) {
        cout << "Invalid unit entered!" << endl;
        return 1;
    }

    double bmi = weightInKg / (heightInMeters * heightInMeters);

    cout << fixed << setprecision(2);
    cout << "\nYour BMI is: " << bmi << endl;
     cout << ""<< endl;
    suggestDiet(bmi);

    return 0;
}
