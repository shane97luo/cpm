<!DOCTYPE html>
<html lang="zh-CN">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>系统信息监控</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <style>
    body {
      font-family: monospace;
      background-color: #000;
      color: #fff;
      margin: 0;
      padding: 0;
    }

   .container {
      width: 90%;
      margin: 0 auto;
      padding: 10px;
    }

   .header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin-bottom: 10px;
    }

   .system-info {
      display: flex;
    }

   .system-info div {
      margin-right: 20px;
    }

   .info-block {
      border: 1px solid #444;
      padding: 10px;
      border-radius: 5px;
    }

   .cpu-info,
   .mem-info,
   .swap-info,
   .load-info {
      display: flex;
      flex-direction: column;
    }

   .task-table {
      width: 100%;
      border-collapse: collapse;
    }

   .task-table th,
   .task-table td {
      border: 1px solid #444;
      padding: 8px;
      text-align: left;
    }

   .task-table th {
      background-color: #333;
    }

   .network-info,
   .disk-info,
   .file-system-info,
   .process-info {
      margin-top: 10px;
    }

   .alert-info {
      margin-top: 10px;
      padding: 10px;
      border: 1px solid #444;
      border-radius: 5px;
    }

   .chart-container {
      width: 100%;
      max-width: 400px;
      margin: 0 auto;
    }
  </style>
</head>

<body>
  <div id="app" class="container">
    <div class="header">
      <div class="system-info">
        <div class="info-block">
          <p>11th Gen Intel(R) Core(TM) i5-11400H @ 2.70GHz</p>
          <p>2688/0Ghz</p>
        </div>
        <div class="info-block cpu-info">
          <p>CPU</p>
          <p>{{ cpuUsage }}%</p>
          <p>user: {{ cpuUser }}%</p>
          <p>system: {{ cpuSystem }}%</p>
          <p>iowait: {{ cpuIowait }}%</p>
          <p>idle: {{ cpuIdle }}%</p>
          <p>ctx_sw: {{ cpuCtxSw }}</p>
        </div>
        <div class="info-block mem-info">
          <p>MEM</p>
          <p>{{ memUsage }}%</p>
          <p>total: {{ memTotal }}G</p>
          <p>used: {{ memUsed }}G</p>
          <p>free: {{ memFree }}G</p>
          <p>active: {{ memActive }}M</p>
          <p>inactive: {{ memInactive }}G</p>
          <p>buffers: {{ memBuffers }}M</p>
          <p>cached: {{ memCached }}M</p>
        </div>
        <div class="info-block swap-info">
          <p>SWAP</p>
          <p>{{ swapUsage }}%</p>
          <p>total: {{ swapTotal }}G</p>
          <p>used: {{ swapUsed }}G</p>
          <p>free: {{ swapFree }}G</p>
        </div>
        <div class="info-block load-info">
          <p>LOAD</p>
          <p>12-core</p>
          <p>1 min: {{ load1m }}</p>
          <p>5 min: {{ load5m }}</p>
          <p>15 min: {{ load15m }}</p>
        </div>
      </div>
      <div class="info-block">
        <p>2025-01-19 13:19:33 CST</p>
        <p>Uptime: 6:22:00</p>
      </div>
    </div>
    <div class="chart-container">
      <canvas id="cpuMemChart"></canvas>
    </div>
    <div class="network-info info-block">
      <p>NETWORK</p>
      <p>eth0</p>
      <p>Rps: {{ networkRps }}kb</p>
      <p>Txs: {{ networkTxs }}kb</p>
    </div>
    <div class="disk-info info-block">
      <p>DISK I/O</p>
      <table class="task-table">
        <thead>
          <tr>
            <th>Device</th>
            <th>Rps</th>
            <th>Wps</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="(disk, index) in disks" :key="index">
            <td>{{ disk.device }}</td>
            <td>{{ disk.rps }}kb</td>
            <td>{{ disk.wps }}kb</td>
          </tr>
        </tbody>
      </table>
    </div>
    <div class="file-system-info info-block">
      <p>FILE SYSTEM</p>
      <table class="task-table">
        <thead>
          <tr>
            <th>Mount Point</th>
            <th>Used</th>
            <th>Total</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="(fs, index) in fileSystems" :key="index">
            <td>{{ fs.mountPoint }}</td>
            <td>{{ fs.used }}G</td>
            <td>{{ fs.total }}G</td>
          </tr>
        </tbody>
      </table>
    </div>
    <div class="process-info info-block">
      <p>TASKS</p>
      <table class="task-table">
        <thead>
          <tr>
            <th>PID</th>
            <th>USER</th>
            <th>%CPU</th>
            <th>%MEM</th>
            <th>VIRT</th>
            <th>RES</th>
            <th>COMMAND</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="(process, index) in processes" :key="index">
            <td>{{ process.pid }}</td>
            <td>{{ process.user }}</td>
            <td>{{ process.cpuUsage }}%</td>
            <td>{{ process.memUsage }}%</td>
            <td>{{ process.virt }}M</td>
            <td>{{ process.res }}M</td>
            <td>{{ process.command }}</td>
          </tr>
        </tbody>
      </table>
    </div>
    <div class="alert-info">
      <p>NO warning or critical alert detected</p>
    </div>
  </div>
  <script src="https://unpkg.com/vue@3/dist/vue.global.js"></script>
  <script>
    const app = Vue.createApp({
      setup() {
        // CPU 信息
        const cpuUsage = Vue.ref('0.3');
        const cpuUser = Vue.ref('0.2');
        const cpuSystem = Vue.ref('0.1');
        const cpuIowait = Vue.ref('0');
        const cpuIdle = Vue.ref('99.7');
        const cpuCtxSw = Vue.ref('354');

        // 内存信息
        const memUsage = Vue.ref('36.4');
        const memTotal = Vue.ref('7.65');
        const memUsed = Vue.ref('2.80');
        const memFree = Vue.ref('4.85');
        const memActive = Vue.ref('124');
        const memInactive = Vue.ref('2.40');
        const memBuffers = Vue.ref('17.8');
        const memCached = Vue.ref('421');

        // 交换空间信息
        const swapUsage = Vue.ref('0');
        const swapTotal = Vue.ref('2.00');
        const swapUsed = Vue.ref('0');
        const swapFree = Vue.ref('2.00');

        // 系统负载信息
        const load1m = Vue.ref('0.06');
        const load5m = Vue.ref('0.02');
        const load15m = Vue.ref('0.02');

        // 网络信息
        const networkRps = Vue.ref('70');
        const networkTxs = Vue.ref('70');

        // 磁盘 I/O 信息
        const disks = Vue.ref([
          { device: 'loop0', rps: '1.2', wps: '0.6' },
          { device: 'loop1', rps: '1.8', wps: '0.9' },
          { device:'sda', rps: '0.2', wps: '0.1' }
        ]);

        // 文件系统信息
        const fileSystems = Vue.ref([
          { mountPoint: '/', used: '41.0', total: '100.0' },
          { mountPoint: '/mnt/wslg', used: '41.0', total: '100.0' },
          { mountPoint: '/snap', used: '1.6', total: '10.0' }
        ]);

        // 进程信息
        const processes = Vue.ref([
          { pid: 1234, user: 'user1', cpuUsage: '1.2', memUsage: '0.5', virt: '1024', res: '512', command: 'process1' },
          { pid: 5678, user: 'user2', cpuUsage: '0.8', memUsage: '0.3', virt: '800', res: '300', command: 'process2' },
          { pid: 9012, user: 'user3', cpuUsage: '2.0', memUsage: '0.7', virt: '1500', res: '700', command: 'process3' }
        ]);

        // 绘制图表
        const drawChart = () => {
          const ctx = document.getElementById('cpuMemChart').getContext('2d');
          new Chart(ctx, {
            type: 'bar',
            data: {
              labels: ['CPU 使用率', '内存使用率'],
              datasets: [{
                label: '使用率',
                data: [parseFloat(cpuUsage.value), parseFloat(memUsage.value)],
                backgroundColor: ['rgba(75, 192, 192, 0.2)', 'rgba(255, 99, 132, 0.2)'],
                borderColor: ['rgba(75, 192, 192, 1)', 'rgba(255, 99, 132, 1)'],
                borderWidth: 1
              }]
            },
            options: {
              scales: {
                y: {
                  beginAtZero: true,
                  max: 100
                }
              }
            }
          });
        };

        // 在组件挂载后绘制图表
        const { onMounted } = Vue;
        onMounted(() => {
          drawChart();
        });

        return {
          cpuUsage,
          cpuUser,
          cpuSystem,
          cpuIowait,
          cpuIdle,
          cpuCtxSw,
          memUsage,
          memTotal,
          memUsed,
          memFree,
          memActive,
          memInactive,
          memBuffers,
          memCached,
          swapUsage,
          swapTotal,
          swapUsed,
          swapFree,
          load1m,
          load5m,
          load15m,
          networkRps,
          networkTxs,
          disks,
          fileSystems,
          processes
        };
      }
    });

    app.mount('#app');
  </script>
</body>

</html>