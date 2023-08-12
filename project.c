#include <stdio.h>
#include <string.h>
#include <ctype.h>

void displayMenu() {
    printf("\nATM Simulator\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

void formatBalance(float balance, char formattedBalance[]) {
    int integerPart = (int)balance;
    int remainderPart = (int)((balance - integerPart) * 100);
    sprintf(formattedBalance, "%d.%02d", integerPart, remainderPart);
}

int main() {
    float balance_debit = 100000.0;
    float balance_credit = 50000.0;
    const float credit_limit = 200000.0;
    const float max_credit_withdraw = 500000.0;
    int choice;
    float amount;
    int passwordAttempts = 3;
    int password;
    char cardType;

    printf("Welcome to the ATM Simulator\n");

    do {
        printf("Please enter 'D' for Debit Card or 'C' for Credit Card: ");
        scanf(" %c", &cardType);

        cardType = toupper(cardType);

        printf("Please enter your password: ");
        scanf("%d", &password);

        if ((cardType == 'D') && password == 5566) {
            printf("Debit Card accepted. You are now logged in.\n");
            break;
        } else if ((cardType == 'C') && password == 6565) {
            printf("Credit Card accepted. You are now logged in.\n");
            break;
        } else {
            passwordAttempts--;
            printf("Incorrect card type or password. %d attempts remaining.\n", passwordAttempts);
        }
    } while (passwordAttempts > 0);

    if (passwordAttempts == 0) {
        printf("You have exceeded the maximum number of attempts. Exiting...\n");
        return 0;
    }

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                if (cardType == 'D') {
                    char formattedBalance[20];
                    formatBalance(balance_debit, formattedBalance);
                    printf("Your debit card balance is: Rs %s\n", formattedBalance);
                } else if (cardType == 'C') {
                    char formattedBalance[20];
                    formatBalance(balance_credit, formattedBalance);
                    printf("Your credit card balance is: Rs %s\n", formattedBalance);
                    char formattedLimit[20];
                    formatBalance(credit_limit, formattedLimit);
                    printf("Credit card limit: Rs %s\n", formattedLimit);
                } else {
                    printf("Invalid card type. Exiting...\n");
                    return 0;
                }
                break;
            }
            case 2: {
                printf("Enter the amount to deposit: ");
                scanf("%f", &amount);
                if (amount > 0) {
                    if (cardType == 'D') {
                        balance_debit += amount;
                        char formattedBalance[20];
                        formatBalance(balance_debit, formattedBalance);
                        printf("Deposit successful. Your new debit card balance is: Rs %s\n", formattedBalance);
                    } else if (cardType == 'C') {
                        balance_credit += amount;
                        char formattedBalance[20];
                        formatBalance(balance_credit, formattedBalance);
                        printf("Deposit successful. Your new credit card balance is: Rs %s\n", formattedBalance);
                    } else {
                        printf("Invalid card type. Exiting...\n");
                        return 0;
                    }
                } else {
                    printf("Invalid amount. Please enter a positive value.\n");
                }
                break;
            }
            case 3: {
                printf("Enter the amount to withdraw: ");
                scanf("%f", &amount);
                if (amount > 0) {
                    if (cardType == 'D') {
                        if (balance_debit >= amount) {
                            balance_debit -= amount;
                            char formattedBalance[20];
                            formatBalance(balance_debit, formattedBalance);
                            printf("Withdrawal successful. Your new debit card balance is: Rs %s\n", formattedBalance);
                        } else {
                            printf("Insufficient debit card balance. Cannot withdraw.\n");
                        }
                    } else if (cardType == 'C') {
                        if (amount <= max_credit_withdraw) {
                            if (balance_credit >= amount) {
                                balance_credit -= amount;
                                char formattedBalance[20];
                                formatBalance(balance_credit, formattedBalance);
                                printf("Withdrawal successful. Your new credit card balance is: Rs %s\n", formattedBalance);
                            } else {
                                printf("Insufficient credit card balance. Cannot withdraw.\n");
                            }
                        } else {
                            printf("Withdrawal amount exceeds the maximum limit. Cannot withdraw.\n");
                        }
                    } else {
                        printf("Invalid card type. Exiting...\n");
                        return 0;
                    }
                } else {
                    printf("Invalid amount. Please enter a positive value.\n");
                }
                break;
            }
            case 4: {
                printf("Thank you for using the ATM Simulator. Have a nice day!\n");
                return 0;
            }
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}
