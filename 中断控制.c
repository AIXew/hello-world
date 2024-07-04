__weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4) == 0)
	{
//		HAL_Delay(10);
//		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4) == 0)
//		{
			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_5);
//			OneNet_SendData();			//不可以无序中断嵌套，注意优先级
//		}
	}
	
}