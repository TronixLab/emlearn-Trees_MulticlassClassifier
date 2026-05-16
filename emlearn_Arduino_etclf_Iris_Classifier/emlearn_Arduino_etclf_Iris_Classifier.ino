#include "ExtraTreesClassifier.h"

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
    double features[4];
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
      features[featureIndex] = value.toDouble();
      featureIndex++;
      if (commaIndex == -1) break;
      lastIndex = commaIndex + 1;
    }

    // Print parsed features
    Serial.print("Features: ");
    for (int i = 0; i < 4; i++) {
      Serial.print(features[i], 2);
      if (i < 3) Serial.print(", ");
    }

    // Predict the class label for the input features
    Serial.print("\t Prediction: ");
    int32_t y_pred = ExtraTreesClassifier_predict(features, sizeof(features) / sizeof(features[0]));
    Serial.print(classes[y_pred]);
 
    // Compute the probabilities for each class
    Serial.print("\t Probability: ");
    int err = ExtraTreesClassifier_predict_proba(features, sizeof(features) / sizeof(features[0]), proba, sizeof(classes) / sizeof(classes[0]));

    if (err == 0) {
      Serial.print(proba[y_pred] * 100.00, 2);
      Serial.println("%");
    }
  }
  delay(100);
}