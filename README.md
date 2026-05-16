# emlearn Trees Multiclass Classifier

A TinyML-focused example project that trains tree-based multiclass classifiers on the Iris dataset, converts them to portable C code with [emlearn](https://github.com/emlearn/emlearn), and deploys them as Arduino sketches.

## Why this repository matters for TinyML

This repository shows a practical TinyML workflow built around classic machine learning instead of deep learning:

- train compact **Decision Tree**, **Random Forest**, and **Extra Trees** models with scikit-learn
- evaluate multiclass classification performance on the Iris dataset
- convert trained models into **plain C/C++ header files** with emlearn
- run inference on Arduino by sending feature values over the serial monitor

It is a good reference for embedded developers who want to deploy lightweight classifiers on microcontrollers with limited RAM, flash, and compute.

## Repository contents

| Path | Description |
| --- | --- |
| `Iris_Ensemble_Classification.ipynb` | Main notebook for data exploration, training, evaluation, visualization, and model export |
| `Iris_Ensemble_Classification.html` | Rendered HTML version of the notebook |
| `iris.csv` | Iris dataset used for training and testing |
| `emlearn_Arduino_dtclf_Iris_Classifier/` | Arduino sketch and generated header for the Decision Tree model |
| `emlearn_Arduino_rfclf_Iris_Classifier/` | Arduino sketch and generated header for the Random Forest model |
| `emlearn_Arduino_etclf_Iris_Classifier/` | Arduino sketch and generated header for the Extra Trees model |
| `TINYML_OVERVIEW.md` | TinyML-oriented project overview and deployment notes |

## TinyML pipeline in this project

1. Load and inspect the Iris dataset with pandas.
2. Visualize feature distributions and class separation.
3. Split the dataset using `test_size=0.20`, `random_state=43`, and stratification.
4. Train three tree-based classifiers:
   - `DecisionTreeClassifier(max_depth=10, random_state=42)`
   - `RandomForestClassifier(n_estimators=30, max_depth=10, random_state=42)`
   - `ExtraTreesClassifier(n_estimators=30, max_depth=10, random_state=42)`
5. Evaluate accuracy, precision, recall, F1 score, and confusion matrices.
6. Convert the trained models to embedded-friendly headers with emlearn.
7. Use the generated Arduino sketches to classify live feature input over serial.

## Performance snapshot

The exported notebook reports the following test metrics:

| Model | Accuracy | Precision | Recall | F1 Score |
| --- | --- | --- | --- | --- |
| Decision Tree | 96.67% | 96.97% | 96.67% | 96.66% |
| Random Forest | 96.67% | 96.97% | 96.67% | 96.66% |
| Extra Trees | 93.33% | 93.33% | 93.33% | 93.33% |

These results make the repository useful for comparing the tradeoff between **model simplicity**, **ensemble robustness**, and **embedded footprint**.

## Arduino inference workflow

Each Arduino sketch:

- starts serial communication at `9600` baud
- expects one comma-separated line with four Iris features
- performs on-device inference using the emlearn-generated model
- prints the predicted class and class probability

Example serial input:

```text
5.1,3.5,1.4,0.2
```

Example output pattern:

```text
Prediction: Iris-Setosa
```

## TinyML footprint insight

The generated model headers illustrate how model choice affects embedded size:

- Decision Tree header: about **2.6 KB**
- Random Forest header: about **40.7 KB**
- Extra Trees header: about **110.5 KB**

This makes the repository especially valuable for learning how accuracy and model diversity must be balanced against flash usage in TinyML deployments.

## How to use this repository

### Explore the training workflow

Open the notebook:

- `Iris_Ensemble_Classification.ipynb`
- or the rendered HTML report at `Iris_Ensemble_Classification.html`

### Run on Arduino

1. Open one of the `.ino` projects in the Arduino IDE.
2. Compile and upload it to your board.
3. Open the Serial Monitor at `9600` baud.
4. Send four comma-separated floating-point values from the Iris feature set.
5. Read the predicted species and reported probability.

## Python packages used in the notebook

The notebook uses these main Python libraries:

- pandas
- seaborn
- matplotlib
- scikit-learn
- emlearn

## Additional documentation

For a TinyML-oriented explanation of the project structure, deployment flow, and model tradeoffs, see:

- `TINYML_OVERVIEW.md`
