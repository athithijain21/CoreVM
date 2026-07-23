document.addEventListener('DOMContentLoaded', () => {
    console.log('CoreVM Web Dashboard Loaded Successfully.');

    // 1. Copy Code Functionality
    const copyBtn = document.getElementById('copy-btn');
    const codeBlock = document.querySelector('code');

    if (copyBtn && codeBlock) {
        copyBtn.addEventListener('click', () => {
            const codeText = codeBlock.innerText;

            navigator.clipboard.writeText(codeText).then(() => {
                const originalText = copyBtn.innerText;
                copyBtn.innerText = 'Copied!';
                copyBtn.style.backgroundColor = '#1f6feb';

                setTimeout(() => {
                    copyBtn.innerText = originalText;
                    copyBtn.style.backgroundColor = '#238636';
                }, 2000);
            }).catch(err => {
                console.error('Failed to copy code: ', err);
            });
        });
    }

    // 2. Simulated Dynamic Terminal Message
    const statusOutput = document.getElementById('status-output');
    if (statusOutput) {
        const timestamp = new Date().toLocaleTimeString();
        console.log(`[${timestamp}] CoreVM Status: SYSTEM READY`);
    }
});