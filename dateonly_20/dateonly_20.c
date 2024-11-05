#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdint.h>

// Helper function to get the days in a given month and year
static int days_in_month(int month, int year) {
    switch (month) {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        default:
            return 31;
    }
}

// Function to encode a date
static PyObject* encode_date(PyObject* self, PyObject* args) {
    int year, month, day;
    if (!PyArg_ParseTuple(args, "iii", &year, &month, &day)) {
        return NULL;
    }
    if (year < 1900 || year > 2027 || month < 1 || month > 12 || day < 1 || day > 31) {
        PyErr_SetString(PyExc_ValueError, "Invalid date.");
        return NULL;
    }
    uint8_t year_offset = (uint8_t)(year - 1900);
    uint16_t encoded_date = (year_offset << 9) | (month << 5) | day;
    return PyLong_FromUnsignedLong((unsigned long)encoded_date);
}

// Function to decode a date
static PyObject* decode_date(PyObject* self, PyObject* args) {
    unsigned int encoded_date;
    if (!PyArg_ParseTuple(args, "I", &encoded_date)) {
        return NULL;
    }
    uint8_t year_offset = (encoded_date >> 9) & 0x7F;
    uint8_t month = (encoded_date >> 5) & 0x0F;
    uint8_t day = encoded_date & 0x1F;
    int year = year_offset + 1900;
    return Py_BuildValue("iii", year, month, day);
}

// Function to add to a date
static PyObject* add_date(PyObject* self, PyObject* args) {
    int encoded_date, add_years, add_months, add_days;
    if (!PyArg_ParseTuple(args, "iiii", &encoded_date, &add_years, &add_months, &add_days)) {
        return NULL;
    }

    uint8_t year_offset = (encoded_date >> 9) & 0x7F;
    uint8_t month = (encoded_date >> 5) & 0x0F;
    uint8_t day = encoded_date & 0x1F;

    int year = year_offset + 1900;
    year += add_years;
    month += add_months;
    day += add_days;

    while (month > 12) {
        month -= 12;
        year += 1;
    }
    while (month < 1) {
        month += 12;
        year -= 1;
    }

    // Adjust day and handle overflow based on days in the month
    while (day > days_in_month(month, year)) {
        day -= days_in_month(month, year);
        month += 1;
        if (month > 12) {
            month = 1;
            year += 1;
        }
    }

    if (year < 1900 || year > 2027) {
        PyErr_SetString(PyExc_ValueError, "Invalid resulting date.");
        return NULL;
    }

    uint8_t new_year_offset = (uint8_t)(year - 1900);
    uint16_t new_encoded_date = (new_year_offset << 9) | (month << 5) | day;
    return PyLong_FromUnsignedLong((unsigned long)new_encoded_date);
}

// Function to parse YYYY-MM-DD format
static PyObject* parse_date(PyObject* self, PyObject* args) {
    const char* date_str;
    int year, month, day;
    if (!PyArg_ParseTuple(args, "s", &date_str)) {
        return NULL;
    }
    if (sscanf(date_str, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        PyErr_SetString(PyExc_ValueError, "Date must be in YYYY-MM-DD format.");
        return NULL;
    }
    PyObject *date_tuple = Py_BuildValue("iii", year, month, day);
    if (!date_tuple) {
        return NULL;
    }
    PyObject *encoded_date = encode_date(self, date_tuple);
    Py_DECREF(date_tuple);  // Free the temporary date tuple

    return encoded_date;
}

// Function to convert encoded date to string "YYYY-MM-DD"
static PyObject* date_to_iso_string(PyObject* self, PyObject* args) {
    unsigned int encoded_date;
    if (!PyArg_ParseTuple(args, "I", &encoded_date)) {
        return NULL;
    }

    uint8_t year_offset = (encoded_date >> 9) & 0x7F;
    uint8_t month = (encoded_date >> 5) & 0x0F;
    uint8_t day = encoded_date & 0x1F;
    int year = year_offset + 1900;

    char date_str[11];
    snprintf(date_str, sizeof(date_str), "%04d-%02d-%02d", year, month, day);

    return PyUnicode_FromString(date_str);
}

// Method definitions
static PyMethodDef DateMethods[] = {
    {"encode_date", encode_date, METH_VARARGS, "Encode a date into a 16-bit integer."},
    {"decode_date", decode_date, METH_VARARGS, "Decode a 16-bit integer into a date."},
    {"add_date", add_date, METH_VARARGS, "Add years, months, and days to a date."},
    {"parse_date", parse_date, METH_VARARGS, "Parse a date in YYYY-MM-DD format and encode it."},
    {"date_to_iso_string", date_to_iso_string, METH_VARARGS, "Convert an encoded date to a string in YYYY-MM-DD format."},
    {NULL, NULL, 0, NULL}
};

// Module definition
static struct PyModuleDef dateonly_20module = {
    PyModuleDef_HEAD_INIT,
    "dateonly_20.dateonly_20", 
    NULL,
    -1,
    DateMethods
};

PyMODINIT_FUNC PyInit_dateonly_20(void) {
    return PyModule_Create(&dateonly_20module);
}
