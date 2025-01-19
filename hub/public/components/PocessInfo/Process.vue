<template>
    <div class="system-info">
        <h2>System Information</h2>
        <p>CPU Usage: {{ cpuUsage }}%</p>
        <p>Memory Usage: {{ memoryUsage }} MB</p>
        <!-- 更多的系统信息 -->
    </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted } from 'vue';
import axios from 'axios';

const cpuUsage = ref(10);
const memoryUsage = ref(10);

const fetchSystemInfo = async () => {
    try {
        const response = await axios.get('http://your-backend-api/system-info');
        // cpuUsage.value = response.data.cpu;
        // memoryUsage.value = response.data.memory;
    } catch (error) {
        console.error('Failed to fetch system info', error);
    }
};

// 挂载时获取一次数据，并每隔5秒更新一次
let intervalId;
onMounted(() => {
    fetchSystemInfo();
    intervalId = setInterval(fetchSystemInfo, 5000); // 每5秒刷新一次
});

// 组件卸载时清除定时器
onUnmounted(() => {
    clearInterval(intervalId);
});
</script>

<style scoped>
.system-info {
    font-family: Arial, sans-serif;
}
</style>