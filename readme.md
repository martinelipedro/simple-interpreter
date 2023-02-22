# simple-interpreter

A simple interpreter, made with C, completely handwritten and commented in Portuguese!

🇧🇷 O código comentado será futuramente adicionado a uma nova branch!

## Example: 

```
variable = 'hello world!';
variable_number = 5 * 15 + 10;
print(variable, 'other line string', variable_number);
```

## Out
```
hello world!
other line string
85
```

# Known Bugs

- variable = other_variable doesn't work yet
- it is still only possible to perform calculations with 1 operation of each type (term, expr, factor)
- generating a noop node at the beginning of the program
- integers represented as floats (that was my laziness)
  
# Compilation

just run make lol