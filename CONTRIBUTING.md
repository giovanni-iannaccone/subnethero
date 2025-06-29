# 🧩 Contributing
We welcome contributions! Please follow these steps:

1. Fork the repository.
2. Create a new branch ( using <a href="https://medium.com/@abhay.pixolo/naming-conventions-for-git-branches-a-cheatsheet-8549feca2534">this</a> convention).
3. Make your changes and commit them with descriptive messages.
4. Push your changes to your fork.
5. Create a pull request to the main repository.

## 👨‍💻 Development guidelines
- **Modularity**: functions should be small and focused on a single responsibility
- **Separation of Concerns**: maintain clear separation between business logic and utility functions
- **Dependency-low**: implement every function which is not in the standard library from scratch
- **Documentation**: add comments to explain complex logic
- **Prevent memory leaks**: analyze the program with valgrind and ensure no memory leak is possible

## 🎨 Code style
- **Naming**: use snake_case for function and variables names
- **Clarity and Consistency**: keep variable and function names descriptive, avoid unnecessary abbreviations
- **Types**: specify varibles types in declaration where it doesn't look redoundaunt
- **Formatting**: ensure your code is properly formatted
- **Imports**: organize imports into two sections:
    - Standard library packages
    - Internal project packages

Ensure all your tests pass before submitting a PR.

These guidelines are designed to keep the codebase readable, maintainable, and consistent, even when multiple developers contribute. Following a common style helps reduce errors and makes the code easier to understand for others in the team. If you'd like to add more specific guidelines or have questions, feel free to ask!

Thank you for contributing to subnethero! Your efforts are deeply appreciated. If you have any questions, feel free to reach out in the project discussions or open an issue.