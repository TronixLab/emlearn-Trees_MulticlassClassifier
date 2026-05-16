# TinyML Overview

## Project summary

This repository demonstrates how to take a classical multiclass machine learning problem and deploy it in a TinyML setting.

The workflow starts with the Iris flower dataset, trains tree-based classifiers in Python, evaluates their performance, and then uses **emlearn** to convert the final models into C/C++ code that can run on Arduino-class hardware.

## Why this is TinyML

TinyML is about running machine learning models on highly resource-constrained devices such as microcontrollers. This repository fits that theme because it focuses on:

- **small input vectors** with only four sensor-like features
- **lightweight tree-based models** that do not require floating-point heavy neural network runtimes
- **direct C/C++ code generation** instead of depending on large inference frameworks
- **serial-based on-device inference** that can be tested immediately on embedded boards

## End-to-end workflow

### 1. Data preparation and exploration

The notebook reads `iris.csv`, examines class distributions, and visualizes the separability of flower features. This step helps explain why compact tree models are a good fit for the dataset.

### 2. Model training

Three multiclass classifiers are trained:

- Decision Tree
- Random Forest
- Extra Trees

The repository uses shallow, bounded-depth models and moderate ensemble sizes, which is important when the final target is an embedded device.

### 3. Performance evaluation

The notebook compares the models with standard classification metrics and confusion matrices. In the exported results, the Decision Tree and Random Forest achieve the best reported test accuracy at **96.67%**, while Extra Trees reaches **93.33%**.

### 4. Conversion with emlearn

After training, each model is converted with emlearn into a generated header file:

- `DecisionTreeClassifier.h`
- `RandomForestClassifier.h`
- `ExtraTreesClassifier.h`

These files contain prediction functions that can be compiled directly into Arduino sketches.

### 5. Embedded inference

Each Arduino sketch reads comma-separated feature values over the serial port, calls the generated predictor, and prints the predicted iris class and confidence value.

## Repository artifacts through a TinyML lens

| Artifact | TinyML relevance |
| --- | --- |
| `Iris_Ensemble_Classification.ipynb` | Shows the complete train-evaluate-convert workflow |
| `Iris_Ensemble_Classification.html` | Easy-to-share static report of the notebook results |
| `iris.csv` | Compact benchmark dataset for multiclass classification |
| `DecisionTreeClassifier.h` | Smallest generated model and best candidate for low-flash targets |
| `RandomForestClassifier.h` | Larger ensemble model for comparing accuracy versus size |
| `ExtraTreesClassifier.h` | Most randomized ensemble and the largest exported artifact |
| Arduino `.ino` sketches | Ready-made embedded inference entry points |

## Embedded tradeoffs visible in this repository

One of the strongest TinyML lessons in this project is the tradeoff between **model complexity** and **deployment footprint**.

Approximate generated header sizes:

- Decision Tree: **2.6 KB**
- Random Forest: **40.7 KB**
- Extra Trees: **110.5 KB**

This shows that even when model accuracy is similar, memory footprint can vary dramatically. For very small MCUs, the single Decision Tree may be the most practical option. For boards with more flash memory, ensemble models provide a useful comparison point.

## Best audience for this repository

This project is a strong reference for:

- embedded developers learning TinyML without starting from neural networks
- students comparing classical ML models before deployment
- makers who want a serial-driven Arduino inference demo
- engineers evaluating whether emlearn is suitable for compact scikit-learn models

## Suggested next TinyML extensions

If this repository is expanded later, useful next steps would include:

- benchmarking inference latency on specific microcontroller boards
- recording RAM and flash consumption after compilation
- testing integer or quantized feature pipelines where possible
- comparing emlearn-generated code with other TinyML deployment approaches
- adding a hardware demonstration with real sensor data instead of CSV input

## Key takeaway

This repository is a compact example of a real TinyML deployment pattern: train in Python, export to C, and run multiclass inference on a microcontroller with minimal runtime overhead.
