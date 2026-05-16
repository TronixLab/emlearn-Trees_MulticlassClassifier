#include "DecisionTreeClassifier.h"

// Class labels for the Iris dataset
const char *classes[3] = { "Iris-Setosa", "Iris-Versicolor", "Iris-Virginica" };

// Array to hold probabilities for each class
float proba[3];

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Parse CSV format input features from the serial monitor
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    float features[4];
    int featureIndex = 0;
    int lastIndex = 0;
    line.trim();

    while (featureIndex < 4) {
      int commaIndex = line.indexOf(',', lastIndex);
      String value;
      if (commaIndex == -1) {
        value = line.substring(lastIndex);
      } else {
        value = line.substring(lastIndex, commaIndex);
      }
      features[featureIndex] = value.toFloat();
      featureIndex++;
      if (commaIndex == -1) break;
      lastIndex = commaIndex + 1;
    }

    // Predict the class label for the input features
    Serial.print("Prediction: ");
    int32_t y_pred = DecisionTreeClassifier_predict(features, sizeof(features) / sizeof(features[0]));
    Serial.print(classes[y_pred]);
 
    // Compute the probabilities for each class
    Serial.print("\t Probability: ");
    int err = DecisionTreeClassifier_predict_proba(features, sizeof(features) / sizeof(features[0]), proba, sizeof(classes) / sizeof(classes[0]));

    if (err == 0) {
      Serial.println(proba[y_pred]);
    }
  }
  delay(100);
}