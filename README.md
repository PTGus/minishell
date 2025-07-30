<h1 align="center">🐚 Minishell – As Beautiful as a Shell</h1>

<p align="center">
  <em>A POSIX-compliant miniature shell built in C, from scratch.</em>
</p>

---

## 📖 About the Project

**Minishell** is a project from the 42 core curriculum that consists of building a simplified, POSIX-compliant Unix shell written entirely in C.  
The goal is to recreate the basic behavior of `bash`, deepening understanding of:

- Processes and forking
- File descriptors and redirections
- Signals and terminal control
- Command parsing and environment expansion
- Low-level system programming

This project strictly follows the 42 Norm, ensuring clean, robust, and maintainable C code with careful memory management and signal safety.

---

## 📌 Project Goals

- Reimplement a basic command-line shell from scratch.
- Parse and interpret user input, respecting quoting rules and Bash-like behavior.
- Execute commands using `PATH` resolution or absolute/relative paths.
- Handle system calls for process and I/O management.
- Implement essential built-in shell features.
- Manage signals and user interaction gracefully.

---

## ✅ Features Implemented

<details>
<summary>🔹 <strong>Command Execution</strong></summary>

- Executes binaries found in the `PATH`, or via absolute/relative paths.
- Supports foreground process execution.
- Allows command chaining through pipes (`|`).
</details>

<details>
<summary>🔹 <strong>Built-in Commands</strong></summary>

- `echo` with `-n` option  
- `cd` (relative/absolute path support)  
- `pwd`  
- `export`  
- `unset`  
- `env`  
- `exit`  
</details>

<details>
<summary>🔹 <strong>Redirections</strong></summary>

- `<`  — input redirection  
- `>`  — output redirection  
- `>>` — append output redirection  
- `<<` — heredoc (with proper delimiter and quoting support)  
</details>

<details>
<summary>🔹 <strong>Pipelines</strong></summary>

- Supports `|` operator to chain commands together.  
- Proper use of `pipe()` and `dup2()` for data redirection between commands.
</details>

<details>
<summary>🔹 <strong>Environment Variable Expansion</strong></summary>

- Expands `$VAR` from current environment.  
- Expands `$?` to reflect the last command’s exit status.
</details>

<details>
<summary>🔹 <strong>Quoting Rules</strong></summary>

- Single quotes `'...'` disable all expansions.  
- Double quotes `"..."` preserve all characters except `$`.
</details>

<details>
<summary>🔹 <strong>Signal Handling</strong></summary>

- `Ctrl+C` → Interrupts current command and displays a new prompt  
- `Ctrl+D` → Exits the shell  
- `Ctrl+\` → Ignored (default behavior)  
- Uses only **one** global variable for signal communication (as per the subject)
</details>

---

## 💻 Technical Notes

- 📌 Written in **C**, with no use of `system()` or similar high-level functions.
- 📚 Uses only allowed external functions (`readline`, `execve`, `fork`, `pipe`, etc.).
- ✅ Fully Norm-compliant (42 coding standard).
- 🔐 No memory leaks — validated with `valgrind`.
- 🛠️ Fully functional and strict `Makefile` with:
  - `all`, `clean`, `fclean`, `re`, `bonus`

---

## 🔒 Constraints

- ❌ No segmentation faults or undefined behavior
- 🔄 No unnecessary recompilation in the Makefile
- 📁 Only one global variable allowed (for signal handling)
- ✅ Must behave exactly like Bash when specified (e.g., signals, quoting, environment)
- 📦 Bonus features only graded if the mandatory part is 100% correct

---

## 🧠 What We Learned

- ✅ Deep understanding of process management: `fork`, `execve`, `waitpid`, etc.
- ✅ Safe and correct use of file descriptors and pipes
- ✅ Signal-safe programming in an interactive environment
- ✅ Manual parsing and tokenization logic
- ✅ Careful memory management in long-running programs
- ✅ The inner workings of how a Unix shell interprets and runs commands

---

## 📁 Project Structure
```
minishell/
├── srcs/
│   ├── built_in/
│   ├── clean_up/
│   ├── commands/
│   ├── err_handling/
│   ├── main/
│   ├── parsing/
│   ├── pipes/
│   ├── redirections/
│   ├── signals/
│   └── utils/
├── include/
│   ├── types.h/
│   └── minishell.h
├── libft/         # A copy of our libft cloned during build process
├── Makefile
├── notes.txt      # Some notes taken during the making of the project
└── README.md
```
---

<h3>⚙️ Installation</h3>

<pre><code>git clone git@github.com:PTGus/minishell.git
cd minishell
make
</code></pre>

<p>💡 Make sure you have <code>readline</code> installed:</p>

<ul>
  <li>On macOS: <code>brew install readline</code></li>
  <li>On Debian/Ubuntu: <code>sudo apt install libreadline-dev</code></li>
</ul>

<h3>🚀 Usage</h3>

<p>After compiling, launch the shell with:</p>

<pre><code>./minishell
</code></pre>

<p>From here, you can:</p>

<ul>
  <li>Run built-in commands: <code>cd</code>, <code>echo</code>, <code>pwd</code>, <code>exit</code>, etc.</li>
  <li>Execute binaries from the <code>PATH</code>: <code>ls</code>, <code>grep</code>, <code>cat</code>, etc.</li>
  <li>Use input/output redirection and pipelines</li>
  <li>Expand environment variables with <code>$</code>, including <code>$?</code></li>
  <li>Use signal shortcuts like:
    <ul>
      <li><code>Ctrl+C</code> to cancel</li>
      <li><code>Ctrl+D</code> to exit</li>
      <li><code>Ctrl+\</code> to ignore</li>
    </ul>
  </li>
</ul>

<p>To exit the shell:</p>

<pre><code>exit
</code></pre>

---

<h3>📚 Reference</h3>

<blockquote>
  <em>“With Minishell, you’ll travel back in time and experience the challenges developers faced before Windows existed.”</em>
</blockquote>

<p>
  This project is based on the official 42 School
  <a href="https://cdn.intra.42.fr/pdf/pdf/169449/en.subject.pdf" target="_blank" rel="noopener noreferrer"><strong>subject</strong></a> (v9.1).
  It aims to mimic the core behavior of <strong>Bash</strong>, but implemented entirely from scratch using system-level <strong>C programming</strong>.
</p>

<p>
  This deep dive into <strong>Unix fundamentals</strong> helped us strengthen our understanding of:
</p>

<ul>
  <li>Process control (<code>fork</code>, <code>execve</code>, <code>waitpid</code>)</li>
  <li>File descriptors and redirections</li>
  <li>Signal-safe interactive applications</li>
  <li>Command parsing and environment variable expansion</li>
  <li>Writing robust CLI tools from the ground up</li>
</ul>

---

## 👨‍💻 Contributors

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/PTGus">
        <img src="https://avatars.githubusercontent.com/u/177729576?s=400&v=4" width="100px;" alt="PTGus"/>
        <br /><sub><b>Gustavo Cunha</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Vazalos">
        <img src="https://avatars.githubusercontent.com/u/23241859?v=4" width="100px;" alt="Vazalos"/>
        <br /><sub><b>David Roque</b></sub>
      </a>
    </td>
  </tr>
</table>

---
