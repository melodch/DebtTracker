Debt Tracking Application in C
 
The goal for our project was to create a debt tracker program that allows users to track their expenses within a group over time. Our intention with making this program is for student groups to be able to keep track of how much money each person owes or is owed by each of the other group members. A debt tracker is something that is something useful that we would use within our suite, and we can imagine it being useful to other people who need to keep track of monetary exchanges. Our MVP is a working program that will be able to keep track of debt and manage certain users through a local terminal, and our ideal final product is to have an application that incorporates a friendlier UI.
 
The learning goal we set out to achieve by working on this project was to develop a better understanding of program development in C. We specifically wanted to learn about how to manage data flow and how to store data in a way that can be accessed and manipulated in an application built in C.
 
To get started, we looked at existing software that performs the same task of debt tracking, namely, Splitwise. This helped us choose which features we wanted to include in our program. We decided to further define our MVP as being a program that carries out these six basic functions:


[input file](../CSV/input.c)
[action file](../CSV/action.c)
[main file](../CSV/main.c)



![alt text for screen readers](images/Miro.jpg "Choosing program features")

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

