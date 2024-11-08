# DateOnly 20

A Python C extension for encoding, decoding, and manipulating 20th-century dates with high performance. This module provides efficient functions for date encoding into a compact format, decoding back to standard date representations, and performing arithmetic operations like adding years, months, and days.

[![Build Python Extension](https://github.com/IshamMohamed/dateonly_20/actions/workflows/build.yml/badge.svg)](https://github.com/IshamMohamed/dateonly_20/actions/workflows/build.yml)
## Features

- **Encode Dates**: Convert dates into a 16-bit integer representation.
- **Decode Dates**: Retrieve standard date components from the encoded format.
- **Date Arithmetic**: Add years, months, and days while handling overflow correctly.
- **Date Parsing**: Convert dates from the `YYYY-MM-DD` string format into the encoded format.
- **ISO String Conversion**: Easily convert encoded dates back to `YYYY-MM-DD` format.

## Installation

To install the module, clone the repository and run the following based on the scenario:

### Prod usage
```bash
pip install dateonly-20
```

### Test and debug
```bash
python setup.py build_ext --inplace   # Compile C code
python setup.py install               # Install the module
```

## Usage
Here’s a simple example of how to use the module:

```python
import dateonly_20

# Encode a date
encoded = dateonly_20.encode_date(2023, 11, 3)

# Decode the encoded date
year, month, day = dateonly_20.decode_date(encoded)

# Add 1 year, 2 months, and 15 days to the encoded date
new_date = dateonly_20.add_date(encoded, 1, 2, 15)

# Convert the encoded date to a string in YYYY-MM-DD format
date_str = dateonly_20.date_to_iso_string(encoded)
```
![Untitled](https://github.com/user-attachments/assets/4b1cacd9-ffaf-4d00-ac38-1b73454095d1)


