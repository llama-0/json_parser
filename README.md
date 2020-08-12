# This is a custom json_parser for a Ray Tracing project

### Build & Run
```make; ./parse [example.json]```

### Key features:
- reused dictionary data strucure with minimal adaptation (previously built for [minishell project])
- parsing of strings, numbers, arrays implemented
- number types available for parsing:
  - -123
  - 0.8
  - 1.78e4
  - 674E-1
- main data structure is a linked list
- architecture has easily expandable blocks
- somewhat user friendly error handling

### Deliberate omission had been made to array type values which represent coordinates:
- array values are 'double', so there couldn't be values like:
  - ["10.0", 0, -0.8] --> strings, even if the value inside is a double
  - ["5.3", "4", "3"] --> all are strings, even if all values inside are double
  - [2, [34.5], 0] --> arrays, even if the value inside is double
  - [[5.3], [4], [3]] --> all are arrays, even if all values inside are double
### Empty objects, arrays are forbidden
In a ray tracer source file we expect values to be present in order to be able to draw a picture on the screen (no values - no sense).
If some important data is missing, the parser will notify you about it.
    
### Not a bug, but a feature
If you placed `-` sign inside an array like this [10.0, 0,- 0.8] validation will parse it OK, because the first step of validation is to remove all whitespaces (thus we less memory is used to store initial data)

[minishell project]: https://github.com/llama-0/minishell
