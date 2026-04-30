const input = document.getElementById("input");
const output = document.getElementById("output");
const promptLabel = document.getElementById("prompt-label");

function print(text) {
    text.split("\n").forEach(line => {
        const div = document.createElement("div");
        div.innerHTML = formatLine(line);
        output.appendChild(div);
    });

    output.scrollTop = output.scrollHeight;
}

function formatLine(line) {
    return line.replace(
        /(https?:\/\/[^\s]+)/g,
        url => `<a href="${url}" target="_blank">${url}</a>`
    );
}

function handleCommand(cmd) {
    const result = Module.ccall(
        "process_command",
        "string",
        ["string"],
        [cmd]
    );

    handleOutput(result);
}

function handleOutput(text) {
    const windowMatch = text.match(/\[OPEN_WINDOW:(.+?)\]/);

    if (windowMatch) {
        const projectName = windowMatch[1];
        openProjectWindow(projectName);
    }

    const cleaned = text.replace(/\[OPEN_WINDOW:.*?\]/, "");
    print(cleaned);
}

function openProjectWindow(name) {
    const img = document.getElementById("preview-img");
    img.style.transition = "opacity 0.5s ease-in-out";
    img.style.opacity = 0;

    setTimeout(() => {
        img.src = "resources/" + name + ".png";
        img.onload = () => { img.style.opacity = 1; };
    }, 100);
}

function updatePrompt() {
    try {
        if (promptLabel && typeof Module.ccall === 'function') {
            const path = Module.ccall("get_current_path", "string", []);
            promptLabel.innerText = path;
        }
    } catch (e) {
        console.error("Error updating prompt:", e);
    }
}

input.addEventListener("keydown", function (e) {
    if (e.key === "Enter") {
        const cmd = input.value.trim();
        const currentPath = promptLabel ? promptLabel.innerText : "Root";

        print(currentPath + " > " + cmd);

        handleCommand(cmd);
        updatePrompt();

        input.value = "";
        input.focus();
    }
});