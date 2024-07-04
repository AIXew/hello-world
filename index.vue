<template>
	<view class="wrapper">
		<view class="device-area">
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">温度</view>
					<image class="device-logo" src="/static/Temp.png"></image>
				</view>
				<view class="device-data">{{Temp}}℃</view>
			</view>
			
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">湿度</view>
					<image class="device-logo" src="/static/Humi.png"></image>
				</view>
				<view class="device-data">{{Humi}}%</view>
			</view>
			
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">台灯</view>
					<image class="device-logo" src="/static/Lamp.png"></image>
				</view>
				<switch :checked="status" @change="onLedSwitch" color="#2b9939"/>
			</view>
		
		
			<view class="content">
				<image class="logo" src="/static//beautiful.png"></image>
				<view class="text-area">
					<text class="title">{{title}}</text>
				</view>
			</view>
		
			
		</view>
		
	</view>
</template>
 
<script>
	export default {
		data() {
			return {
				Temp: 0,
				Humi: 0,
				Led: false,
				status: false,
				title: 'ikun'
			}
		},
		onShow() {
			let that = this
			this.GetDatapoints()
			setInterval(function(){
				that.GetDatapoints()
				}, 3000);			//请求快一点3S
		},
		
		onLoad() {
					
		},
		methods: {
			GetDatapoints: function(){ 
				uni.request({
				    url: 'http://api.heclouds.com/devices/1004695102/datapoints?', //仅为示例，并非真实接口地址。
				
				    header: {
				        'api-key': 'yADWnwACOo9EzEf0D=nq=54drSw=' //自定义请求头信息
				    },
					method: 'GET',
				    success: (res) => {
				  //       console.log(res.data);
						// console.log(res.data.data.datastreams[1].id, res.data.data.datastreams[1].datapoints[0].value);
						// console.log(res.data.data.datastreams[0].id, res.data.data.datastreams[0].datapoints[0].value);
						this.Temp = res.data.data.datastreams[2].datapoints[0].value;		//解析数据
						this.Humi = res.data.data.datastreams[1].datapoints[0].value;		//解析数据
						this.Led = res.data.data.datastreams[3].datapoints[0].value;
						// console.log(res.data.data.datastreams[3].id, Boolean(res.data.data.datastreams[3].datapoints[0].value));
						// console.log(res.data.data.datastreams[3].id, res.data.data.datastreams[3].datapoints[0].value);
						// console.log(this.Led);
						if(this.Led == 1)
						{
							this.status = true;
							// console.log(this.status);
						}
						else
						{
							this.status = false;
							// console.log(this.status);
						}
						// console.log(Boolean(this.Led));
						// console.log(this.Led);
					}
				});
			},
			onLedSwitch(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;
				if(sw) {
					uni.request({
					    url: 'http://api.heclouds.com/mqtt?topic=LED_SW', 
					
					    header: {
					        'api-key': 'wWUFkpg2dNRcJmzBXgY8ATMacRM=' //Master-key
					    },
						method: 'POST',
						data: {"LED":1},
					    success: (res) => {
					        console.log("LED on!");
					    }
					});
				}
				else {
					uni.request({
					    url: 'http://api.heclouds.com/mqtt?topic=LED_SW', 
					    header: {
					        'api-key': 'wWUFkpg2dNRcJmzBXgY8ATMacRM=' //Master-key
					    },
						method: 'POST',
						data: {"LED":0},
					    success: (res) => {
					        console.log("LED off!");
					    }
					});
				}
			}
 
		}
	}
</script>
 
<style>
	.wrapper {
		padding: 30rpx;
	}
 
	.device-area {
		display: flex;
		justify-content: space-between;
		flex-wrap: wrap;
	}
 
	.device-cart {
		width: 320rpx;
		height: 150rpx;
		border-radius: 30rpx;
		margin-top: 30rpx;
		display: flex;
		justify-content: space-around;
		align-items: center;
		/* background-color: #8f8f94; */
		box-shadow: 0 0 15rpx #ccc;
	}
 
	.device-info {
		font-size: 20rpx;
		/* background-color: #8f8f94; */
	}
	
	.device-name{
		text-align: center;
		color: #6d6d6d;
	}
	.device-logo{
		width: 70rpx;
		height: 70rpx;
		margin-top: 10rpx;
	}
	.device-data{
		font-size: 50rpx;
		color: #6d6d6d;
		
	}
	
	/* 鸡你太美logo 我是ikun，不需要的可以删除下面4段 */
	.content {
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
	}
	
	.logo {
		height: 357rpx;
		width: 357rpx;
		margin-top: 100rpx;
/* 		align-items: center; */
		margin-left: 150rpx;
		margin-right: 40rpx;
		margin-bottom: 50rpx;
	}
	
	.text-area {
		display: flex;
		justify-content: center;
		margin-top: 0rpx;
		margin-left: 150rpx;
		margin-right: 40rpx;
	}
	
	.title {
		font-size: 72rpx;
		color: #8f8f94;
	}
</style>