# Debt Tracker <br>
## Team Members: Walter Villa, Melody Chiu

### Project Goals <br>
Our goal for this project is to create a program that is useful to students. A debt tracker is something useful that we would use within our suite, and we can imagine it being useful to other people who need to keep track of monetary exchanges. We're also interested in having a user-interactive aspect to our project which our application achieves by taking in user input and outputs information that is useful to them.
*MVP and stretch goal*

### Learning Goals <br>
Through this project, we hope to become more comfortable programming in C. We would like to learn about how to manage data flow in an application built in C.

### Getting Started <br>
A major starting resource is online research into existing data management applications. This will give us information on which data structures would be useful for our application and how to implement them in C. We would also like to consult the teaching team on where would be a good place to begin tackling our project.

### Currently working on <br>
We're currently working on making sure that user input is stored and is able to be used to manipulate values from within the csv and txt files. Our MVP is a product that allows us to track changing values for at least 2 people and output a bill for each person. To deepen our project, we can work on expanding the application to include more individuals. Walter is working on using pointers to be able to get information around in functions. He is also trying to lay out how information can be retrieved once the user has inputted one round of information. Melody is thinking about how data can be stored in a csv and is working on functions for csv creation and manipulation. This is done when the function can interface with Walter's work to take in user-input and update the csv.

[input file](../CSV/input.c)
[action file](../CSV/action.c)
[main file](../CSV/main.c)



![alt text for screen readers](/image/Miro.jpg "Choosing program features")

```
while (fgets(line, MAXLINE, fp)) {
    column = 0;
    strcpy(buffer, line);
    char* value = strtok(buffer, " \n");
    while (value) {
        if (column == c && row == r) {
            int num = atoi(value);
            num += change;
            fprintf(new_fp, "%d ", num);
        }
        else if (column == r && row == c) {
            int num = atoi(value);
            num -= change;
            fprintf(new_fp, "%d ", num);
        }
        else (fprintf(new_fp,"%s ", value));
        value = strtok(NULL, " \n");
        column++;
    }
    fprintf(new_fp,"\n");
    row++;
}
```

