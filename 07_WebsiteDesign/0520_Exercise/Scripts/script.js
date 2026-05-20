// script.js
// 1. 透過 ID 找到網頁中的「按鈕」與「背景容器」
const toggleBtn = document.getElementById('toggle-btn');
const background = document.getElementById('background');

// 2. 幫按鈕加上「點擊監聽器 (Event Listener)」
toggleBtn.addEventListener('click', function() {
    
    // 3. 檢查目前背景是否有 'light-theme' 這個 Class
    if (background.classList.contains('light-theme')) {
        // 如果是白天，就換成夜間
        background.classList.remove('light-theme');
        background.classList.add('dark-theme');
        toggleBtn.textContent = '切換至白天模式'; // 順便改掉按鈕文字
    } else {
        // 如果是夜間，就換回白天
        background.classList.remove('dark-theme');
        background.classList.add('light-theme');
        toggleBtn.textContent = '切換至夜間模式';
    }
});